# Server to Client Protocol
----

### Message format:
  [2-letter command]:[arguments, : separated]\r\n
  
  Example: **LA***:*Phoenix Wright from PW5*:*c48c29157e2b358cc144027f3e2d8cb4*\r\n*

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


----
----
# Client to Server Protocol
----

### Message format:
  [2-letter command]:[arguments, : separated]\r\n
  
  Example: **CB***:*Chatbox*:*I like the Ace Attorney franchise!*\r\n*
  
### Command list:

 - **H**and**S**hake (message)
   The first command to be sent between the client and the server. Message is an optional parameter that can be passed by the **GT** command.

 - **C**all**B**ack (ID, args)
   Is sent whenever an interactive layer fires its callback. ID is the identifier of the interactive layer, args are the arguments it passes.
