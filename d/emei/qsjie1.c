//Room: qsjie1.c ��ʯ��
inherit ROOM;

void create()
{
      set("short","��ʯ��");
      set("long",@LONG
�쵽����ɽ�ˡ�����һ��ͨ������ɽ����ʯ�ף�����������Σ�����ʮ��
���¡�ʱ���ܼ���Щ������͡�
LONG);
      set("objects", ([
	       __DIR__+"npc/youngwoman": 1,
	       __DIR__+"npc/puren": 1,
      ]));
      set("outdoors", "emei");
      set("exits",([ /* sizeof() == 1 */
	  "west"       : "/d/city3/road1",
	  "north"      : __DIR__"xiaolu2",
	  "southwest"  : __DIR__"qsjie2",
      ]));
      setup();
}

