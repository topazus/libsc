/*
  This file is part of the SC Library.
  The SC Library provides support for parallel scientific applications.

  Copyright (C) 2010 The University of Texas System
  Additional copyright (C) 2011 individual authors

  The SC Library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  The SC Library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with the SC Library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
*/

#ifndef SC_NOTIFY_H
#define SC_NOTIFY_H

#include <sc_containers.h>

SC_EXTERN_C_BEGIN;

/** Opaque object used for controlling notification (AKA dynamic sparse data exchange) operations */
typedef struct sc_notify_s sc_notify_t;

/** Existing implementations */
typedef enum
{
  SC_NOTIFY_DEFAULT = -1,  /**< choose whatever type is stored in sc_notify_type_default */
  SC_NOTIFY_ALLGATHER = 0, /**< choose allgather algorithm */
  SC_NOTIFY_BINARY,        /**< choose simple binary recursion */
  SC_NOTIFY_NARY,          /**< choose nary (k-way) recursion */
  SC_NOTIFY_ALLTOALL,      /**< choose alltoall algorithm (AKA personalized exchange) */
  SC_NOTIFY_PCX,           /**< choose reduce_scatter algorithm (AKA personalized consensus) */
  SC_NOTIFY_NUM_TYPES
}
sc_notify_type_t;

/** Names for each notify method */
extern const char  *sc_notify_type_strings[SC_NOTIFY_NUM_TYPES];

/** The default type used when constructing a notify controller.  Initialized
 * to SC_NOTIFY_NARY */
extern sc_notify_type_t sc_notify_type_default;

/** The default threshold for payload sizes (in bytes) that are communicated
 * with the notification packet.  Initialized to 1024 (2^10) */
extern size_t       sc_notify_eager_threshold_default;

/** Create a notify controller that can be used in sc_notify_payload() and
 * sc_notify_payloadv().
 *
 * \param[in] mpicomm     The mpi communicator over which the notification occurs.
 * \return                pointer to a notify controller, that should be
 *                        destroyed with sc_notify_destroy().
 */
sc_notify_t        *sc_notify_new (sc_MPI_Comm mpicomm);

/** Destroy a notify controller constructed with sc_notify_create().
 *
 * \param[in,out] notify  The notify controller that will be
 *                        destroyed.  Pointer is invalid on completion.
 */
void                sc_notify_destroy (sc_notify_t * notify);

/** Get the payload size above which payloads are no longer transfered with
 * notification packets in sc_notify_payload().  Default is 256k bytes.
 *
 * \param[in] notify      The notify controller.
 * \return                The size in bytes of the maximum eager payload size.
 */
size_t              sc_notify_get_eager_threshold (sc_notify_t * notify);

/** Get the payload size above which payloads are no longer transfered with
 * notification packets in sc_notify_payload().
 *
 * \param[in,out] notify      The notify controller.
 * \param[in]     thresh      The size in bytes of the maximum eager payload
 *                            size.
 */
void                sc_notify_set_eager_threshold (sc_notify_t * notify,
                                                   size_t thresh);

/** Get the MPI communicator of a notify controller.
 *
 * \param[in] notify   The notify controller.
 * \return             The mpi communicator over which the notification
 *                     occurs.
 */
sc_MPI_Comm         sc_notify_get_comm (sc_notify_t * notify);

/** Get the type of a notify controller.
 *
 * \param[in] notify   The notify controller.
 * \return             The type of the notify controller (see \a sc_notify_type_t).
 */
sc_notify_type_t    sc_notify_get_type (sc_notify_t * notify);

/** Set the type of a notify controller.
 *
 * \param[in,out] notify   The notify controller.
 * \param[in]     type     The type of algorithm used to affect the dynamic
 *                         sparse data exchange.
 */
void                sc_notify_set_type (sc_notify_t * notify,
                                        sc_notify_type_t type);

/** Default number of children at root node of nary tree; initialized to 2 */
extern int          sc_notify_nary_ntop_default;

/** Default number of children at intermediate tree nodes; initialized to 2 */
extern int          sc_notify_nary_nint_default;

/** Default number of children at deepest level of tree; initialized to 2 */
extern int          sc_notify_nary_nbot_default;

/** For a notify of type SC_NOTIFY_NARY, get the branching widths of the
 * recursive algorithm.
 *
 * \param[in] notify  The notify controller.
 * \param[out] ntop   The number of children at root node of nary tree.
 * \param[out] nint   The number of children at intermediate tree nodes.
 * \param[out] nbot   The number of children at deepest level of the tree.
 */
void                sc_notify_nary_get_widths (sc_notify_t * notify,
                                               int *ntop, int *nint,
                                               int *nbot);

/** For a notify of type SC_NOTIFY_NARY, set the branching widths of the
 * recursive algorithm.
 *
 * \param[in,out] notify  The notify controller.
 * \param[in] ntop   The number of children at root node of nary tree.
 * \param[in] nint   The number of children at intermediate tree nodes.
 * \param[in] nbot   The number of children at deepest level of the tree.
 */
void                sc_notify_nary_set_widths (sc_notify_t * notify, int ntop,
                                               int nint, int nbot);

/** Collective call to notify a set of receiver ranks of current rank.
 * This version uses one call to sc_MPI_Allgather and one to sc_MPI_Allgatherv.
 * We provide hand-coded alternatives \ref sc_notify and \ref sc_notify_nary.
 * \param [in] receivers        Array of MPI ranks to inform.
 * \param [in] num_receivers    Count of ranks contained in receivers.
 * \param [in,out] senders      Array of at least size sc_MPI_Comm_size.
 *                              On output it contains the notifying ranks.
 * \param [out] num_senders     On output the number of notifying ranks.
 * \param [in] mpicomm          MPI communicator to use.
 * \return                      Aborts on MPI error or returns sc_MPI_SUCCESS.
 */
int                 sc_notify_allgather (int *receivers, int num_receivers,
                                         int *senders, int *num_senders,
                                         sc_MPI_Comm mpicomm);

/** Collective call to notify a set of receiver ranks of current rank.
 * More generally, this function serves to transpose the nonzero pattern of a
 * matrix, where each row and column corresponds to an MPI rank in order.
 * We use a binary tree to construct the communication pattern.
 * This minimizes the number of messages at the cost of more messages
 * compared to a fatter tree such as configurable with \ref sc_notify_nary.
 * \param [in] receivers        Sorted and unique array of MPI ranks to inform.
 * \param [in] num_receivers    Count of ranks contained in receivers.
 * \param [in,out] senders      Array of at least size sc_MPI_Comm_size.
 *                              On output it contains the notifying ranks,
 *                              whose number is returned in \b num_senders.
 * \param [out] num_senders     On output the number of notifying ranks.
 * \param [in] mpicomm          MPI communicator to use.
 * \return                      Aborts on MPI error or returns sc_MPI_SUCCESS.
 */
int                 sc_notify (int *receivers, int num_receivers,
                               int *senders, int *num_senders,
                               sc_MPI_Comm mpicomm);

/** Collective call to notify a set of receiver ranks of current rank.
 * \param [in,out] receivers    On input, sorted and uniqued array of type int.
 *                              Contains the MPI ranks to inform.
 *                              If \b senders is not NULL, treated read-only.
 *                              If \b senders is NULL, takes its role on output.
 *                              In this case it must not be a view.
 * \param [in,out] senders      If NULL, the result is placed in \b receivers
 *                              as written below for the non-NULL case.
 *                              If not NULL, array of type int and any length.
 *                              Its entries on input are ignored and overwritten.
 *                              On output it is resized to the number of
 *                              notifying ranks, which it contains in order.
 *                              Thus, it must not be a view.
 * \param [in,out] payload      This array pointer may be NULL.
 *                              If not, it must not be a view and have
 *                              \b num_receivers entries that are the
 *                              same size on every process.
 *                              This data will be communicated to the receivers.
 *                              On output, the array is resized to \b
 *                              *num_senders and contains the result.
 * \param [in] notify           Notify controller to use.
 *                              This function aborts on MPI error.
 */
void                sc_notify_payload (sc_array_t * receivers,
                                       sc_array_t * senders,
                                       sc_array_t * payload,
                                       int sorted, sc_notify_t * notify);

/** Collective call to notify a set of receiver ranks of current rank
 * and send a variable size message to the receiver.
 * \param [in,out] receivers    On input, sorted and uniqued array of type int.
 *                              Contains the MPI ranks to inform.
 *                              If \b senders is not NULL, treated read-only.
 *                              If \b senders is NULL, takes its role on output.
 *                              In this case it must not be a view.
 * \param [in,out] senders      If NULL, the result is placed in \b receivers
 *                              as written below for the non-NULL case.
 *                              If not NULL, array of type int and any length.
 *                              Its entries on input are ignored and overwritten.
 *                              On output it is resized to the number of
 *                              notifying ranks, which it contains in order.
 *                              Thus, it must not be a view.
 * \param [in,out] in_payload   This array pointer may be NULL.
 *                              If not, it must not be a view and have
 *                              entries that are the same size on every process.
 *                              This data will be communicated to the receivers.
 *                              If \b out_payload is NULL, this will be
 *                              resized to contain the received payload.
 * \param [in,out] out_payload  This array pointer may be NULL.
 *                              If not, it must not be a view and have
 *                              entries that are the same size on every process.
 *                              If not NULL, this array will be resized to
 *                              contain the received payload.
 * \param [in,out] in_offsets   If \b in_payload is not NULL,
 *                              this is an array of int's of size
 *                              \b num_receivers + 1,
 *                              giving offsets for the portion of the
 *                              payload to be sent to every receiver.
 *                              If \b out_offsets is NULL,
 *                              it will be resized to give
 *                              offsets of the received payload.
 * \param [in,out] out_offsets  This array pointer may be NULL.
 *                              If \b in_payload is not NULL,
 *                              it is an array of int's that will be resized
 *                              to \b num_senders + 1,
 *                              giving offsets for the portion of the
 *                              payload received from each sender.
 * \param [in] sorted           whether \b receivers and \b senders
 *                              (and thus \b in_offsets and \b out_offsets)
 *                              are required to be sorted by MPI rank.
 * \param [in] notify           Notify controller to use.
 *                              This function aborts on MPI error.
 */
void                sc_notify_payloadv (sc_array_t * receivers,
                                        sc_array_t * senders,
                                        sc_array_t * out_payload,
                                        sc_array_t * in_payload,
                                        sc_array_t * out_offsets,
                                        sc_array_t * in_offsets,
                                        int sorted, sc_notify_t * notify);
SC_EXTERN_C_END;

#endif /* !SC_NOTIFY_H */
