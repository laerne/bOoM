Non-specialized messages that agent can output
==============================================



Inter-agent messages
--------------------

* `test_possible_collision( time~t, center~c, radius~r )`

  The entity announce its bounding disk to other entities for possible collision checks.
  Other entities must check if the given bounding disk collide their own bounding disks themselves.

* `tell_possible_collision_detected( time~t, center~c, type~w )`

  The sender announce a possible collision has been detected with the receiver and both must enter a collision check state.
  Nothing prevents an entity to do several collision check at the same time.
  The sender explicitely tells its type so that the receiver can select an algorithm to do the intersection.
  The entities must be careful of the time of the possible detected collision and their own time.
  * Time could be a time span to check ?

* `tell_collision_detected( center~c, bounding_radius~r, ovelapping_area~a, overlapping_mass~m, acceleration~a)`

  A collision has definitively been detected with the given factors.

* `render( origin~c, up~u, right~r, resolution~px_py, render_buffer~surface )`

  The sender, the graphic manager request the receiver object to render itself on the given render buffer.
  (the sender should dispatch the results to the render displays)

* `did_render()`

  Confirmation by the sending entity to the receiving graphic manager that the render is done.
