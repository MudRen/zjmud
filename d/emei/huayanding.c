//Room: huayanding.c ���϶�
inherit ROOM;

void create()
{
      set("short","���϶�");
      set("long",@LONG
���϶�ͦ�θ��ͣ���ɲ���������ʣ��羰���ա�������Ұ����������
����ΡΡ��������Ⱥ�����У����׷�ɽ�����ԺҲ���۵ס��ɴ���������
�£���������ʯ�����¹�ʮ���̿ɵ������¡�������һ����ǡ�
LONG);
      set("objects", ([
	   CLASS_D("emei") + "/li" : 1,
	   __DIR__"npc/girldizi" : 1,
      ]));
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
	  "south"    : __DIR__"majiu2",
	  "northeast"     : __DIR__"shierpan4",
	  "north"     : __DIR__"jingji/enter",
	  "westup"   : __DIR__"lianhuashi",
      ]));
      setup();
}
