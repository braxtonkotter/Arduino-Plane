Plane by Ryan Steed

This code set is built to be integrated into a physical plane, and to maneuver it according to data picked up by the stereo cameras.

Plane.h is a class file for the plane. This includes all methods and information used to fly the plane.
	The Plane uses a 1280 x 800 or 640 x 400 image (undetermined at the moment) comprised of 2 Byte long numbers measured in millimeters.
	This image is split into various other images, each containing a specific range of values found in the origin image.
	These images are used to determine where the plane can safely maneuver.
	On each image, a waypoint is placed in empty space. For the images nearer to the plane, they can under no circumstances be placed in an obstructed space.
	For medium-distance images, empty space is heavily preferred (to avoid a dead-end situation).

	The plane operates in a digital 3d space. It has a location marked at the COM (or calculated COM), measured in cartesian coordinates relative to the point of origin.
	This 3D space exists purely for flight planning purposes.
	A target position is marked somewhere in the 3D space.

	The plane constantly measures and updates position, speed, orientation, and the several control values (such as the servos or the motor)
	All of these values are stored in graph objects.

	The plane will have two servo classes, each coded to the left or right servo. Some member methods will be invoked by the servos if needed.


Graph objects are built in the form of LINKED LISTS. From x = 0 to the final value (no specified X)
	Other important variables are dx (a static increment between values of x), size (how many elements there are in the graph)
	Graph objects keep track of how many objects are recorded.
	When adding to a graph, a vector of values or a single point is accepted.
	If necessary, resizing will change dx, adding points between existing points in a straight line.
	When reading from a graph, a specific index can be targeted, but the default is the first value.

	Translating a graph adds a constant modifier to each point in the graph, or simply makes a two-point modifier graph, the front and end points being the modifier.
		Subgraphs will be used to save time and processing power. When getting a value, the main graph and all subgraphs are factored in.

	Mutation of a graph into another form

	Cartesian-to-polar : takes a cartesian point and makes a new one in the form of a polar coordinate
	Polar-to-cartesian : takes a polar point and makes a new cartesian one 
	Fixed-cartesian-to-relative-cartesian: Each point is defined relative to the previous point, the first value being the base.
	relative-cartesian-to-fixed-cartesian: Each point is defined relative to the first point.

The servo class will have a pointer to a graph of polar coordinates.
	The servo sends information to the Arduino via USB.
	It reads a graph of either CARTESIAN OR POLAR coordinates (UNDECIDED) and performs a reaction to match that line as best as possible.
	If the plane gets too far away from the path, it will need to send the plane a message, telling it to rewrite the line.

The servoRight and servoLeft graphs will be associated with each other, both having a pointer to the other. Possibly with the motor as well.
		
		