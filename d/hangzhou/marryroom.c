// marry_room.c

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "����ׯ");
	set("long", @LONG
��������վ�ڷ�����������Ӻ��ϵĺ���ׯ���ˮƾ��������
���̵ĺ��棬���Ƕ����ˡ�
LONG);
	set("exits", ([
	    "east" : __DIR__"road10",
	]) );

	set("no_fight",1);
	setup();
}

