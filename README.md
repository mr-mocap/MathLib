# MathLib
Simple C++ library for dual numbers, quaternions, and dual quaternions

## Purpose
For exploring the properties of Dual Quaternions and Dual numbers in general.  I may even implement Double numbers as well,
but I don't yet see the use of them.
I decided to create a header-only C++ library for implementing these ideas.

Yes, I know this has been done countless times before, but there's really no better way for me
to understand something than getting down and dirty with an implementation (I noticed that there is
a similar library out there when I was about to put this up).

## Unit Tests
The project contains some unit testing for verifying that I did indeed implement things correctly.
I didn't go for a full unit testing approch.  Rather I just wanted to touch the basics to make sure that
it works in a few specific cases.

## Ideas
1. Conversions
   * Make a Vector3D from a Vector2D with z = 0

2. Classes
   * Point2D & Point3D to mirror the Vector couterparts?  Would this be too many classes with unexpected
     interactions?
   * Plane
   * Ray
   * Sphere

3. Functions
   * cross product
   * Flesh out Quaternion
      * pitch, roll, yaw
      * Euler angles