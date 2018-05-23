MODULE Oberon;

IMPORT Texts;

VAR
  Log*: Texts.Text;
  Par*: RECORD
    text*: Texts.Text;
    pos*: INTEGER
  END;

  PROCEDURE Collect* (count: INTEGER); END Collect;
  PROCEDURE GetSelection* (VAR text: Texts.Text; VAR beg, end, time: INTEGER); END GetSelection;

END Oberon.
