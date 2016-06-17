# Server to Client protocol
----

### Message format:
  [2-letter command]\r[arguments, \r separated]\n
  
  Example: **LA***\r*Phoenix Wright from PW5*\r*c48c29157e2b358cc144027f3e2d8cb4*\n*

### Command list:

 - **L**oad **A**ddon (name, checksum)
   Loads the requested addon and makes it usable in-game.

 - **S**et **L**ayer (wID, ID, depth, type, args)
   Sets the layer of window wID with identifier ID

 - **R**emove **L**ayer (wID, ID)
   Removes layer ID from window wID

 -  **A**dd **W**indow (wID)
   Creates a new game window with window identifier wID

 -  **R**emove **W**indow (wID)
   Removes window wID from the game

 - **G**o**T**o (IP, msg)
   Loads another server at IP, passing it a string msg as a handshake argument
