sqlite2file tool stores internal data specified by the xml schmema into binary file.
* xml schema file example is "./config/schema":
* output binary file format:
<tables_count><table_name1><fields_count><fields><row_count><rows> ... <table_nameN><fields_count><fields><row_count><rows>

Disadvantage:
Requested sqlite data uploads into memory at first and then into binary file. So, there might be some issues on the huge databases - additional implmentaion with chunks/blocks processing is needed.

Usage:
sqlite2file -action serialize|verify -saveset <binary file> [-xmlfile <xml path>] [-show <records count>] [<db source file>]

Examples:
Serialize sqlite db ('./SQLite/db/chinook.db') into binary file ('./saveset.sav'):
> sqlite2file -action serialize -saveset './saveset.sav' -xmlfile './config/schema.xml' './SQLite/db/chinook.db'

Verify binary file ('./saveset.sav') and show up to 20 entries:
> sqlite2file -action verify -saveset './saveset.sav' -show 20