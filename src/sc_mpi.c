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

/* including sc_mpi.h does not work here since sc_mpi.h is included by sc.h */
#include <sc.h>

#ifndef SC_ENABLE_MPI

/* time.h is already included by sc.h */
#ifdef SC_HAVE_SYS_TIME_H
#include <sys/time.h>
#endif
#if defined(SC_HAVE_WINSOCK2_H)
#include <Winsock2.h>
#endif

int
sc_MPI_Init (int *argc, char ***argv)
{
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Init_thread (int *argc, char ***argv, int required, int *provided)
{
  if (provided != NULL) {
    *provided = sc_MPI_THREAD_SINGLE;
  }
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Finalize (void)
{
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Abort (sc_MPI_Comm comm, int exitcode)
{
  abort ();
}

int
sc_MPI_Comm_dup (sc_MPI_Comm comm, sc_MPI_Comm * newcomm)
{
  *newcomm = comm;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Comm_create (sc_MPI_Comm comm, sc_MPI_Group group,
                    sc_MPI_Comm * newcomm)
{
  *newcomm = sc_MPI_COMM_NULL;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Comm_split (sc_MPI_Comm comm, int color, int key,
                   sc_MPI_Comm * newcomm)
{
  *newcomm = comm;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Comm_free (sc_MPI_Comm * comm)
{
  *comm = sc_MPI_COMM_NULL;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Type_size (sc_MPI_Datatype datatype, int *size)
{
  *size = sc_mpi_sizeof (datatype);

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Comm_size (sc_MPI_Comm comm, int *size)
{
  *size = 1;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Comm_rank (sc_MPI_Comm comm, int *rank)
{
  *rank = 0;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Comm_compare (sc_MPI_Comm comm1, sc_MPI_Comm comm2, int *result)
{
  *result = sc_MPI_IDENT;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Comm_group (sc_MPI_Comm comm, sc_MPI_Group * group)
{
  *group = sc_MPI_GROUP_NULL;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_free (sc_MPI_Group * group)
{
  *group = sc_MPI_GROUP_NULL;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_size (sc_MPI_Group group, int *size)
{
  *size = 1;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_rank (sc_MPI_Group group, int *rank)
{
  *rank = 0;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_translate_ranks (sc_MPI_Group group1, int n, int *ranks1,
                              sc_MPI_Group group2, int *ranks2)
{
  int                 i;

  for (i = 0; i < n; i++) {
    ranks2[i] = sc_MPI_UNDEFINED;
  }

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_compare (sc_MPI_Group group1, sc_MPI_Group group2, int *result)
{
  *result = sc_MPI_IDENT;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_union (sc_MPI_Group group1, sc_MPI_Group group2,
                    sc_MPI_Group * newgroup)
{
  *newgroup = sc_MPI_GROUP_NULL;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_intersection (sc_MPI_Group group1, sc_MPI_Group group2,
                           sc_MPI_Group * newgroup)
{
  *newgroup = sc_MPI_GROUP_NULL;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_difference (sc_MPI_Group group1, sc_MPI_Group group2,
                         sc_MPI_Group * newgroup)
{
  *newgroup = sc_MPI_GROUP_NULL;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_incl (sc_MPI_Group group, int n, int *ranks,
                   sc_MPI_Group * newgroup)
{
  *newgroup = sc_MPI_GROUP_NULL;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_excl (sc_MPI_Group group, int n, int *ranks,
                   sc_MPI_Group * newgroup)
{
  *newgroup = sc_MPI_GROUP_NULL;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_range_incl (sc_MPI_Group group, int n, int ranges[][3],
                         sc_MPI_Group * newgroup)
{
  *newgroup = sc_MPI_GROUP_NULL;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Group_range_excl (sc_MPI_Group group, int n, int ranges[][3],
                         sc_MPI_Group * newgroup)
{
  *newgroup = sc_MPI_GROUP_NULL;

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Barrier (sc_MPI_Comm comm)
{
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Bcast (void *p, int n, sc_MPI_Datatype t, int rank, sc_MPI_Comm comm)
{
  SC_ASSERT (rank == 0);

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Gather (void *p, int np, sc_MPI_Datatype tp,
               void *q, int nq, sc_MPI_Datatype tq, int rank,
               sc_MPI_Comm comm)
{
  size_t              lp;
#ifdef SC_ENABLE_DEBUG
  size_t              lq;
#endif

  SC_ASSERT (rank == 0 && np >= 0 && nq >= 0);

/* *INDENT-OFF* horrible indent bug */
  lp = (size_t) np * sc_mpi_sizeof (tp);
#ifdef SC_ENABLE_DEBUG
  lq = (size_t) nq * sc_mpi_sizeof (tq);
#endif
/* *INDENT-ON* */

  SC_ASSERT (lp == lq);
  memcpy (q, p, lp);

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Gatherv (void *p, int np, sc_MPI_Datatype tp,
                void *q, int *recvc, int *displ,
                sc_MPI_Datatype tq, int rank, sc_MPI_Comm comm)
{
  size_t              lp;
#ifdef SC_ENABLE_DEBUG
  size_t              lq;
  int                 nq;

  nq = recvc[0];
#endif
  SC_ASSERT (rank == 0 && np >= 0 && nq >= 0);

/* *INDENT-OFF* horrible indent bug */
  lp = (size_t) np * sc_mpi_sizeof (tp);
#ifdef SC_ENABLE_DEBUG
  lq = (size_t) nq * sc_mpi_sizeof (tq);
#endif
/* *INDENT-ON* */

  SC_ASSERT (lp == lq);
  memcpy ((char *) q + displ[0] * sc_mpi_sizeof (tq), p, lp);

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Allgather (void *p, int np, sc_MPI_Datatype tp,
                  void *q, int nq, sc_MPI_Datatype tq, sc_MPI_Comm comm)
{
  return sc_MPI_Gather (p, np, tp, q, nq, tq, 0, comm);
}

int
sc_MPI_Allgatherv (void *p, int np, sc_MPI_Datatype tp,
                   void *q, int *recvc, int *displ,
                   sc_MPI_Datatype tq, sc_MPI_Comm comm)
{
  return sc_MPI_Gatherv (p, np, tp, q, recvc, displ, tq, 0, comm);
}

int
sc_MPI_Alltoall (void *p, int np, sc_MPI_Datatype tp,
                 void *q, int nq, sc_MPI_Datatype tq, sc_MPI_Comm comm)
{
  return sc_MPI_Gather (p, np, tp, q, nq, tq, 0, comm);
}

int
sc_MPI_Reduce (void *p, void *q, int n, sc_MPI_Datatype t,
               sc_MPI_Op op, int rank, sc_MPI_Comm comm)
{
  size_t              l;

  SC_ASSERT (op != sc_MPI_OP_NULL);
  SC_ASSERT (rank == 0 && n >= 0);

/* *INDENT-OFF* horrible indent bug */
  l = (size_t) n * sc_mpi_sizeof (t);
/* *INDENT-ON* */

  memcpy (q, p, l);

  return sc_MPI_SUCCESS;
}

int
sc_MPI_Reduce_scatter_block (void *p, void *q, int n, sc_MPI_Datatype t,
                             sc_MPI_Op op, sc_MPI_Comm comm)
{
  return sc_MPI_Reduce (p, q, n, t, op, 0, comm);
}

int
sc_MPI_Allreduce (void *p, void *q, int n, sc_MPI_Datatype t,
                  sc_MPI_Op op, sc_MPI_Comm comm)
{
  return sc_MPI_Reduce (p, q, n, t, op, 0, comm);
}

int
sc_MPI_Scan (void *sendbuf, void *recvbuf, int count,
             sc_MPI_Datatype datatype, sc_MPI_Op op, sc_MPI_Comm comm)
{
  return sc_MPI_Reduce (sendbuf, recvbuf, count, datatype, op, 0, comm);
}

/* Exscan recvbuf undefined on proc 0 */
int
sc_MPI_Exscan (void *sendbuf, void *recvbf, int count,
               sc_MPI_Datatype datatype, sc_MPI_Op op, sc_MPI_Comm comm)
{
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Recv (void *buf, int count, sc_MPI_Datatype datatype, int source,
             int tag, sc_MPI_Comm comm, sc_MPI_Status * status)
{
  SC_ABORT ("non-MPI MPI_Recv is not implemented");
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Irecv (void *buf, int count, sc_MPI_Datatype datatype, int source,
              int tag, sc_MPI_Comm comm, sc_MPI_Request * request)
{
  SC_ABORT ("non-MPI MPI_Irecv is not implemented");
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Send (void *buf, int count, sc_MPI_Datatype datatype,
             int dest, int tag, sc_MPI_Comm comm)
{
  SC_ABORT ("non-MPI MPI_Send is not implemented");
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Isend (void *buf, int count, sc_MPI_Datatype datatype, int dest,
              int tag, sc_MPI_Comm comm, sc_MPI_Request * request)
{
  SC_ABORT ("non-MPI MPI_Isend is not implemented");
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Probe (int source, int tag, sc_MPI_Comm comm, sc_MPI_Status * status)
{
  SC_ABORT ("non-MPI MPI_Probe is not implemented");
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Iprobe (int source, int tag, sc_MPI_Comm comm, int *flag,
               sc_MPI_Status * status)
{
  SC_ABORT ("non-MPI MPI_Iprobe is not implemented");
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Get_count (sc_MPI_Status * status, sc_MPI_Datatype datatype,
                  int *count)
{
  SC_ABORT ("non-MPI MPI_Get_count is not implemented");
  return sc_MPI_SUCCESS;
}

int
sc_MPI_Wait (sc_MPI_Request * request, sc_MPI_Status * status)
{
  SC_CHECK_ABORT (*request == sc_MPI_REQUEST_NULL,
                  "non-MPI MPI_Wait handles NULL request only");
  return sc_MPI_SUCCESS;
}

double
sc_MPI_Wtime (void)
{
  int                 retval;
  struct timeval      tv;

  retval = gettimeofday (&tv, NULL);
  SC_CHECK_ABORT (retval == 0, "gettimeofday");

  return (double) tv.tv_sec + 1.e-6 * tv.tv_usec;
}

#else /* SC_ENABLE_MPI */
#ifndef SC_ENABLE_MPITHREAD

/* default to non-threaded operation */

int
sc_MPI_Init_thread (int *argc, char ***argv, int required, int *provided)
{
  if (provided != NULL) {
    *provided = sc_MPI_THREAD_SINGLE;
  }
  return sc_MPI_Init (argc, argv);
}

#endif /* !SC_ENABLE_MPITHREAD */
#endif /* SC_ENABLE_MPI */

int
sc_MPI_Waitsome (int incount, sc_MPI_Request * array_of_requests,
                 int *outcount, int *array_of_indices,
                 sc_MPI_Status * array_of_statuses)
{
#ifdef SC_ENABLE_MPI
  /* we do this to avoid warnings when the prototype uses [] */
  return MPI_Waitsome (incount, array_of_requests, outcount,
                       array_of_indices, array_of_statuses);
#else
  int                 i;

  for (i = 0; i < incount; ++i) {
    SC_CHECK_ABORT (array_of_requests[i] == sc_MPI_REQUEST_NULL,
                    "non-MPI MPI_Waitsome handles NULL requests only");
  }
  *outcount = 0;

  return sc_MPI_SUCCESS;
#endif
}

int
sc_MPI_Waitall (int count, sc_MPI_Request * array_of_requests,
                sc_MPI_Status * array_of_statuses)
{
#ifdef SC_ENABLE_MPI
  /* we do this to avoid warnings when the prototype uses [] */
  return MPI_Waitall (count, array_of_requests, array_of_statuses);
#else
  int                 i;

  for (i = 0; i < count; ++i) {
    SC_CHECK_ABORT (array_of_requests[i] == sc_MPI_REQUEST_NULL,
                    "non-MPI MPI_Waitall handles NULL requests only");
  }
  return sc_MPI_SUCCESS;
#endif
}

int
sc_MPI_Testall (int count, sc_MPI_Request * array_of_requests, int *flag,
                sc_MPI_Status * array_of_statuses)
{
#ifdef SC_ENABLE_MPI
  /* we do this to avoid warnings when the prototype uses [] */
  return MPI_Testall (count, array_of_requests, flag, array_of_statuses);
#else
  int                 i;

  for (i = 0; i < count; ++i) {
    SC_CHECK_ABORT (array_of_requests[i] == sc_MPI_REQUEST_NULL,
                    "non-MPI MPI_Testall handles NULL requests only");
  }
  return sc_MPI_SUCCESS;
#endif
}

int
sc_MPI_Error_class (int errorcode, int *errorclass)
{
#ifdef SC_ENABLE_MPIIO
  /* process error codes unchanged by MPI implementation */
  return MPI_Error_class (errorcode, errorclass);
#else
  if (errorclass == NULL) {
    return sc_MPI_ERR_ARG;
  }

  /* these error classes are understood directly by libsc */
  switch (errorcode) {
  case sc_MPI_SUCCESS:
  case sc_MPI_ERR_ARG:
  case sc_MPI_ERR_UNKNOWN:
  case sc_MPI_ERR_OTHER:
  case sc_MPI_ERR_NO_MEM:
  case sc_MPI_ERR_FILE:
  case sc_MPI_ERR_NOT_SAME:
  case sc_MPI_ERR_AMODE:
  case sc_MPI_ERR_UNSUPPORTED_DATAREP:
  case sc_MPI_ERR_UNSUPPORTED_OPERATION:
  case sc_MPI_ERR_NO_SUCH_FILE:
  case sc_MPI_ERR_FILE_EXISTS:
  case sc_MPI_ERR_BAD_FILE:
  case sc_MPI_ERR_ACCESS:
  case sc_MPI_ERR_NO_SPACE:
  case sc_MPI_ERR_QUOTA:
  case sc_MPI_ERR_READ_ONLY:
  case sc_MPI_ERR_FILE_IN_USE:
  case sc_MPI_ERR_DUP_DATAREP:
  case sc_MPI_ERR_CONVERSION:
  case sc_MPI_ERR_IO:
    *errorclass = errorcode;
    return sc_MPI_SUCCESS;
  }
#ifdef SC_ENABLE_MPI
  /* there may by version 1.1 error codes we do not catch */
  return MPI_Error_class (errorcode, errorclass);
#else
  /* there is no way to produce any other value without MPI */
  return *errorclass = sc_MPI_ERR_UNKNOWN;
#endif
#endif
}

int
sc_MPI_Error_string (int errorcode, char *string, int *resultlen)
{
#ifdef SC_ENABLE_MPIIO
  /* process error codes unchanged by MPI implementation */
  return MPI_Error_string (errorcode, string, resultlen);
#else
  int                 retval;
  const char         *tstr = NULL;

  if (string == NULL || resultlen == NULL) {
    return sc_MPI_ERR_ARG;
  }

  /* these error classes are understood directly by libsc */
  switch (errorcode) {
  case sc_MPI_SUCCESS:
    tstr = "Success";
    break;
  case sc_MPI_ERR_ARG:
    tstr = "Error in function argument";
    break;
  case sc_MPI_ERR_UNKNOWN:
    tstr = "Unknown MPI error";
    break;
  case sc_MPI_ERR_OTHER:
    tstr = "Other MPI error";
    break;
  case sc_MPI_ERR_NO_MEM:
    tstr = "Out of memory";
    break;
  case sc_MPI_ERR_FILE:
    tstr = "Invalid file object";
    break;
  case sc_MPI_ERR_NOT_SAME:
    tstr = "Arguments do not match in parallel";
    break;
  case sc_MPI_ERR_AMODE:
    tstr = "Invalid access mode";
    break;
  case sc_MPI_ERR_UNSUPPORTED_DATAREP:
    tstr = "Unsupported data representation";
    break;
  case sc_MPI_ERR_UNSUPPORTED_OPERATION:
    tstr = "Unsupported operation";
    break;
  case sc_MPI_ERR_NO_SUCH_FILE:
    tstr = "No such file";
    break;
  case sc_MPI_ERR_FILE_EXISTS:
    tstr = "File exists";
    break;
  case sc_MPI_ERR_BAD_FILE:
    tstr = "Bad file name or path";
    break;
  case sc_MPI_ERR_ACCESS:
    tstr = "Permission denied";
    break;
  case sc_MPI_ERR_NO_SPACE:
    tstr = "Out of disk space";
    break;
  case sc_MPI_ERR_QUOTA:
    tstr = "Out of quota";
    break;
  case sc_MPI_ERR_READ_ONLY:
    tstr = "File is read-only";
    break;
  case sc_MPI_ERR_FILE_IN_USE:
    tstr = "File is in use";
    break;
  case sc_MPI_ERR_DUP_DATAREP:
    tstr = "Duplicate data representation";
    break;
  case sc_MPI_ERR_CONVERSION:
    tstr = "File conversion error";
    break;
  case sc_MPI_ERR_IO:
    tstr = "I/O or format error";
    break;
  }
  if (tstr == NULL) {
#ifdef SC_ENABLE_MPI
    /* there may by version 1.1 error codes we do not catch */
    return MPI_Error_string (errorcode, string, resultlen);
#else
    /* there is no way to produce any other value without MPI */
    return sc_MPI_ERR_UNKNOWN;
#endif
  }

  /* print into the output string */
  if ((retval = snprintf (string, sc_MPI_MAX_ERROR_STRING, "%s", tstr)) < 0) {
    /* unless something goes against the current standard of snprintf */
    return sc_MPI_ERR_NO_MEM;
  }
  if (retval >= sc_MPI_MAX_ERROR_STRING) {
    retval = sc_MPI_MAX_ERROR_STRING - 1;
  }
  *resultlen = retval;

  /* we have successfully placed a string in the output variables */
  return sc_MPI_SUCCESS;
#endif
}

size_t
sc_mpi_sizeof (sc_MPI_Datatype t)
{
  if (t == sc_MPI_CHAR)
    return sizeof (char);
  if (t == sc_MPI_BYTE)
    return 1;
  if (t == sc_MPI_SHORT || t == sc_MPI_UNSIGNED_SHORT)
    return sizeof (short);
  if (t == sc_MPI_INT || t == sc_MPI_UNSIGNED)
    return sizeof (int);
  if (t == sc_MPI_LONG || t == sc_MPI_UNSIGNED_LONG)
    return sizeof (long);
  if (t == sc_MPI_LONG_LONG_INT)
    return sizeof (long long);
  if (t == sc_MPI_UNSIGNED_LONG_LONG)
    return sizeof (unsigned long long);
  if (t == sc_MPI_FLOAT)
    return sizeof (float);
  if (t == sc_MPI_DOUBLE)
    return sizeof (double);
  if (t == sc_MPI_LONG_DOUBLE)
    return sizeof (long double);
  if (t == sc_MPI_2INT)
    return 2 * sizeof (int);

  SC_ABORT_NOT_REACHED ();
}

#if defined(SC_ENABLE_MPI) && defined (SC_ENABLE_MPICOMMSHARED)

/* Make this a parameter to sc_mpi_comm_attach_node_comms and friends! */
static int          sc_mpi_node_comm_keyval = sc_MPI_KEYVAL_INVALID;

static int
sc_mpi_node_comms_destroy (sc_MPI_Comm comm, int comm_keyval,
                           void *attribute_val, void *extra_state)
{
  int                 mpiret;
  sc_MPI_Comm        *node_comms = (sc_MPI_Comm *) attribute_val;

  mpiret = sc_MPI_Comm_free (&node_comms[0]);
  if (mpiret != sc_MPI_SUCCESS) {
    return mpiret;
  }
  mpiret = sc_MPI_Comm_free (&node_comms[1]);
  if (mpiret != sc_MPI_SUCCESS) {
    return mpiret;
  }
  mpiret = sc_MPI_Free_mem (node_comms);

  return sc_MPI_SUCCESS;
}

static int
sc_mpi_node_comms_copy (sc_MPI_Comm oldcomm, int comm_keyval,
                        void *extra_state,
                        void *attribute_val_in,
                        void *attribute_val_out, int *flag)
{
  sc_MPI_Comm        *node_comms_in = (sc_MPI_Comm *) attribute_val_in;
  sc_MPI_Comm        *node_comms_out;
  int                 mpiret;

  /* We can't used SC_ALLOC because these might be destroyed after
   * sc finalizes */
  mpiret =
    sc_MPI_Alloc_mem (2 * sizeof (sc_MPI_Comm), sc_MPI_INFO_NULL,
                      &node_comms_out);
  if (mpiret != sc_MPI_SUCCESS) {
    return mpiret;
  }

  mpiret = sc_MPI_Comm_dup (node_comms_in[0], &node_comms_out[0]);
  if (mpiret != sc_MPI_SUCCESS) {
    return mpiret;
  }
  mpiret = sc_MPI_Comm_dup (node_comms_in[1], &node_comms_out[1]);
  if (mpiret != sc_MPI_SUCCESS) {
    return mpiret;
  }

  *((sc_MPI_Comm **) attribute_val_out) = node_comms_out;
  *flag = 1;

  return sc_MPI_SUCCESS;
}

#endif /* SC_ENABLE_MPI && SC_ENABLE_MPICOMMSHARED */

void
sc_mpi_comm_attach_node_comms (sc_MPI_Comm comm, int processes_per_node)
{
#if defined(SC_ENABLE_MPI) && defined (SC_ENABLE_MPICOMMSHARED)
  int                 mpiret, rank, size;
  sc_MPI_Comm        *node_comms, internode, intranode;

  if (sc_mpi_node_comm_keyval == sc_MPI_KEYVAL_INVALID) {
    /* register the node comm attachment with MPI */
    mpiret =
      sc_MPI_Comm_create_keyval (sc_mpi_node_comms_copy,
                                 sc_mpi_node_comms_destroy,
                                 &sc_mpi_node_comm_keyval, NULL);
    SC_CHECK_MPI (mpiret);
  }
  SC_ASSERT (sc_mpi_node_comm_keyval != sc_MPI_KEYVAL_INVALID);

  mpiret = sc_MPI_Comm_size (comm, &size);
  SC_CHECK_MPI (mpiret);
  mpiret = sc_MPI_Comm_rank (comm, &rank);
  SC_CHECK_MPI (mpiret);

  if (processes_per_node < 1) {
    int                 intrasize, intrarank, maxintrasize, minintrasize;

    mpiret =
      sc_MPI_Comm_split_type (comm, sc_MPI_COMM_TYPE_SHARED, rank,
                              sc_MPI_INFO_NULL, &intranode);
    SC_CHECK_MPI (mpiret);

    /* We only accept node comms if they are all the same size */
    mpiret = sc_MPI_Comm_size (intranode, &intrasize);
    SC_CHECK_MPI (mpiret);
    mpiret = sc_MPI_Comm_rank (intranode, &intrarank);
    SC_CHECK_MPI (mpiret);

    mpiret =
      sc_MPI_Allreduce (&intrasize, &maxintrasize, 1, sc_MPI_INT, sc_MPI_MAX,
                        comm);
    SC_CHECK_MPI (mpiret);
    mpiret =
      sc_MPI_Allreduce (&intrasize, &minintrasize, 1, sc_MPI_INT, sc_MPI_MIN,
                        comm);
    SC_CHECK_MPI (mpiret);

    if (maxintrasize != minintrasize) {
      SC_GLOBAL_LDEBUG
        ("node communicators are not the same size: not attaching\n");

      mpiret = sc_MPI_Comm_free (&intranode);
      SC_CHECK_MPI (mpiret);

      return;
    }

    mpiret = sc_MPI_Comm_split (comm, intrarank, rank, &internode);
    SC_CHECK_MPI (mpiret);
  }
  else {
    int                 node, offset;

    SC_ASSERT (!(size % processes_per_node));

    node = rank / processes_per_node;
    offset = rank % processes_per_node;

    mpiret = sc_MPI_Comm_split (comm, node, offset, &intranode);
    SC_CHECK_MPI (mpiret);

    mpiret = sc_MPI_Comm_split (comm, offset, node, &internode);
    SC_CHECK_MPI (mpiret);
  }

  /* We can't used SC_ALLOC because these might be destroyed after
   * sc finalizes */
  mpiret =
    sc_MPI_Alloc_mem (2 * sizeof (sc_MPI_Comm), sc_MPI_INFO_NULL,
                      &node_comms);
  SC_CHECK_MPI (mpiret);
  node_comms[0] = intranode;
  node_comms[1] = internode;

  mpiret = sc_MPI_Comm_set_attr (comm, sc_mpi_node_comm_keyval, node_comms);
  SC_CHECK_MPI (mpiret);
#endif
}

void
sc_mpi_comm_detach_node_comms (sc_MPI_Comm comm)
{
#if defined(SC_ENABLE_MPI) && defined (SC_ENABLE_MPICOMMSHARED)
  if (comm != sc_MPI_COMM_NULL) {
    int                 mpiret;

    mpiret = sc_MPI_Comm_delete_attr (comm, sc_mpi_node_comm_keyval);
    SC_CHECK_MPI (mpiret);
  }
#endif
}

void
sc_mpi_comm_get_node_comms (sc_MPI_Comm comm,
                            sc_MPI_Comm * intranode, sc_MPI_Comm * internode)
{
#if defined(SC_ENABLE_MPI) && defined (SC_ENABLE_MPICOMMSHARED)
  int                 mpiret, flag;
  sc_MPI_Comm        *node_comms;
#endif

  /* default return values */
  *intranode = sc_MPI_COMM_NULL;
  *internode = sc_MPI_COMM_NULL;

#if defined(SC_ENABLE_MPI) && defined (SC_ENABLE_MPICOMMSHARED)
  if (sc_mpi_node_comm_keyval == sc_MPI_KEYVAL_INVALID) {
    return;
  }
  mpiret =
    sc_MPI_Comm_get_attr (comm, sc_mpi_node_comm_keyval, &node_comms, &flag);
  SC_CHECK_MPI (mpiret);
  if (flag && node_comms) {
    *intranode = (sc_MPI_Comm) node_comms[0];
    *internode = (sc_MPI_Comm) node_comms[1];
  }
#endif
}

int
sc_mpi_comm_get_and_attach (sc_MPI_Comm mpicomm)
{
  int                 mpiret;
  int                 intrasize;
  sc_MPI_Comm         intranode, internode;

  /* compute the node comms */
  sc_mpi_comm_attach_node_comms (mpicomm, 0);
  sc_mpi_comm_get_node_comms (mpicomm, &intranode, &internode);

  /* obtain the size of the intra node communicator */
  intrasize = 0;
  if (intranode != sc_MPI_COMM_NULL) {
    mpiret = sc_MPI_Comm_size (intranode, &intrasize);
    SC_CHECK_MPI (mpiret);
  }

  return intrasize;
}
