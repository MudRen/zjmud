//cave1.c
inherit ROOM;

void create()
{
  set("short","�Ҷ���");
  set("long",
	"�������Ҷ��ڲ��������������Ž�׵�����ʯ��\n"
      );
  set("exits",([
      "south" : __DIR__"cave",
     ]));
  set("no_clean_up", 0);
// set("objects",([
//      ]));
 setup();
}




