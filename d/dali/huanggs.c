// /d/dali/huanggs.c �ƹ����ٲ�

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "�ƹ����ٲ�");
	set("long", @LONG
����Ǵ������������µĻƹ����ٲ��������ݺύ���ٲ���
Ⱥ����Ѩ�ɴ������͵��䣬ֲ�����أ����ֳ���ηḻ�Ŀ�˹��ɽ
ˮ�컷�⡣
LONG
	);
	set("outdoors", "dali");

	set("exits", ([
		"east" : __DIR__"feilihusouth",
	]));

	setup();
}
