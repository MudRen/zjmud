// Room: /lingzhou/neizai.c
// by Doing

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "��������լ");
	set("long", @LONG
�����ǽ���������լ�������������һЩС�߷���С·�ľ�������
ԼԼ���ܹ�����һЩ������Ц��ˣ��
LONG );
	set("exits", ([
		"north" : __DIR__"jiangjunyuan",
	]));

	set("objects", ([
		__DIR__"npc/hao" : 1,
	]));
	setup();
}
