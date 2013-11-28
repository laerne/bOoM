/*!
\page rotations Rotation matrices.

A rotation matrix is stored as a pair of a sine \f$s\f$ and a cosine \f$c\f$, for efficiency reasons.
The operation matrix deduced from this sine and cosine is :
\f[
  \left(
  \begin{array}{cc}
     \mathtt{c} & -\mathtt{s} \\
     \mathtt{s} &  \mathtt{c} \\
  \end{array}
  \right).
\f]

Since it has only to remember two components, the rotation matrix can be stored in a vector `V2`.
In that respect, the cosine is stored as the `x` component of the vector and the sine as the `y` component.
This make sense because \f$(c,s)\f$ is the vector obtained by applying the rotation on the unit vector pointing along
the `x`-axis.

Nothing enforce you to use actual sine and cosine values, i.e values such that
\f$\texttt{c}^2+\texttt{s}^2=1\f$.
In the case this last equality is no verified, the matrix represents a
scale-then-rotate operation :
\f[
  \left(
  \begin{array}{cc}
     \mathtt{c} & -\mathtt{s} \\
     \mathtt{s} &  \mathtt{c} \\
  \end{array}
  \right)
=
  \left(
  \begin{array}{cc}
     \frac{\mathtt{c}}{\texttt{c}^2+\texttt{s}^2} &
     \frac{-\mathtt{s}}{\texttt{c}^2+\texttt{s}^2} \\
     \frac{\mathtt{s}}{\texttt{c}^2+\texttt{s}^2} &
     \frac{\mathtt{c}}{\texttt{c}^2+\texttt{s}^2} \\
  \end{array}
  \right)
\cdot
  \left(
  \begin{array}{cc}
     \texttt{c}^2+\texttt{s}^2 & 0 \\
     0 & \texttt{c}^2+\texttt{s}^2 \\
  \end{array}
  \right).
\f]
*/
