//room: liangong3.c

inherit ROOM;

void create()
{
  set("short","Ϸ�����¥");
  set("long",@LONG
��������¥���˱�¥�µ��ٶ��ˣ�ֻ����¥������ԼԼ�Ĵ��������壬
����ô���С�
LONG );
  set("exits",([
      "down" : __DIR__"liangong2",
  ]));
  set("objects",([
      "/clone/npc/mu-ren" : 3
  ]));
  set("for_family", "���չ�");
  setup();
}
