//room: liangong.c

inherit ROOM;

void create()
{
  set("short","Ϸ���");
  set("long",@LONG
���������չ����������ĵط����м�������Ů������ר�����µ����䣬
�м����ֳ��񽣣��ڻ�����У����鶯�����紩������һ�㣬�㲻����
�����ۣ�����������ڵ��ϵ������Ͽ���������
LONG );
  set("exits",([
      "west" : __DIR__"changl4",
      "up"   : __DIR__"liangong2",
  ]));
  set("objects",([
	  "/clone/npc/mu-ren" : 4
  ]));
  set("for_family", "���չ�");
  setup();
}
