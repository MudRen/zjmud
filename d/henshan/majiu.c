//Room: majiu.c ���

#include <room.h>
inherit TRANS_ROOM;

void create()
{
      set("short","���");
      set("long",@LONG
���Ǻ����ǵ���ǣ����깩Ӧ���ʲ��ϡ�����������ϡ���������˺�
�١���������µ���ľ���϶���һ����ľ�ơ�
    ����жѷ������Ѳ��ϣ�������һ����ۡ�
LONG);
      set("outdoors", "henshan");
      set("no_fight", 1);
      set("objects", ([
		"/clone/horse/zaohongma": 1,
		"/clone/horse/huangbiaoma": 1,
		"/clone/horse/ziliuma": 1,
		"/clone/npc/mafu": 1,

      ]));
      set("exits",([ /* sizeof() == 1 */
		"northeast" : __DIR__"hengyang1",
      ]));
      setup();
      replace_program(TRANS_ROOM);
}
