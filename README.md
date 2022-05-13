This project demonstrates a simple inventory system made in UE5

Character has actor component "Inventory Component".
It holds all character's items and has methods for adding items to inventory and consuming it from inventory.

Items are UObjects.
It holds data about amount of the item, stackable attribute and max stack size, displayed name, thumbnail, pickup mesh, displayed name and methods to get and set that data.
Also, it has methods for using item, changing item and on adding to inventory.

Pickups are Actors.
It holds data about the item that'll be added to inventory, mesh in the world. Interaction goes through Interaction Component and trigger sphere. It has methods for taking pickup, for overlap events, initializing pickup on dropping from inventory.

Interaction Component is a Widget Component and shows information about pickups such as name and amount.
