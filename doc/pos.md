An object is a container for stuff we are looking for. For example, if the binary data you want to read only contain an int16, you will define it like this:

Object<main> HelloWorld
       required int16 CustomData

The object is defined as <main>, as it is where Posa will start looking at. The name HelloWorld is just for yourself, unless you want to start using this object with other objects.

The overall syntax for elements you can read/write for each object is the following:
    <constraint> <type> <name>

<contraint> can be made of the following:
  * required: cannot parse the object correctly without this
  * optional: only if some previously defined criterias are set
  * list: a list of objects that repeat in your stream.

Each constraint can take some options, except required:
  * optional needs the condition to be applied to. For example, one can set something like:
    optional int16 foobar if CustomData > 42
  * list can take the number of fixed items it can get, it can either be:
    list<2> object HelloWorld
    which will repeat the HelloWorld object two times.
    Or this can be:
    required int16 listlen
    list<listlen> object HelloWorld, which will repeat the object to parse as a list from listlen.

<type> can be one of the following:
  * byte<n>: reading bytes, with n as the number of bytes to read
  * bit<n>: reading bits, with n as the number of bits to read
  * int8
  * uint8
  * int16
  * uint16
  * int32
  * uint32
  * int64
  * uint64
  * int128
  * uint128
  * string: a string finishing with \0
  * string<stringlen>: take the string length from the wanted <name>
  * unzip <Object>: unzip this data and read it as the object <Object>
  * enum<type>: read variable data of type <type>.
    example: 
      required enum<int16> MyChoice
      	       FOOBAR = 0x01
	       TAGADA = 0x02
	       TSOUIN = 0x04
    
<name> can be anything, as long as there is no space or tab in the name. The name can even start with a number, lowercase/uppercase does not matter.
