// Room: /lingzhou/xiaoyuan.c
// By Doing

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "������СԺ");
	set("long", @LONG
�����ǽ�������СԺ��һɫ����ש�̵أ��м�����������Ժ����
ɨ��ԶԶ�Ĵ���һ����Ц����
LONG );

	set("exits", ([
		"west" : __DIR__"jiangjunyuan",
	]));

	setup();
}
