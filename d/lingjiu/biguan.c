// ROOM : biguan.c
inherit ROOM;
void create()
{
  set("short","�չ���");
  set("long",@LONG
���ǵ�����ɽͯ�ѱչ������ĵط���
LONG );
  set("sleep_room", 1);
  set("exits",([
      "south" : __DIR__"men3",
  ]));
  setup();
}
