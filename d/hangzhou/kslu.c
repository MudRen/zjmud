// kslu.c

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "��ʯ·");
	set("long", @LONG
����һ����ʯ���̾͵�·��·���������������Ŵ󳵣���������
��ʲô��������������ɢɢ��������һЩ��ɫ��ʯͷ���������ǽ���
ʢ��ͭ��ı�ɽ�ˡ�
LONG);
	set("exits", ([
		"west" : __DIR__"road17",
		"east" : __DIR__"kslu2",
	]));
	set("outdoors", "hangzhou");
	setup();
}
