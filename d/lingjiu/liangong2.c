//room: liangong2.c

inherit ROOM;

void create()
{
  set("short","Ϸ����¥");
  set("long",@LONG
���������չ����������ĵط����м�������Ů������ר�����µ����䣬
�м����ֳ��񽣣��ڻ�����У����鶯�����紩������һ�㣬�㿴��Ҳ
�̲�סԾԾ���ԡ�
LONG );
  set("exits",([
      "down" : __DIR__"liangong",
      "up"   : __DIR__"liangong3",
  ]));
  set("objects",([
      "/clone/npc/mu-ren" : 4
  ]));
  set("for_family", "���չ�");
  setup();
}
