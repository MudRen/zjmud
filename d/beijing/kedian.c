#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�͵�");
	set("long", @LONG
����һ�ҹ�ģ��С�Ŀ͵꣬����İ���Ҳ�൱�ĳ¾ɺͼ�ª���͵���ϰ�
��һ����ͷ����Ϊ���С��ĳɱ�С����ͷҲ��û�������˰�æ���͵������
һ�ж��������ڴ����͵�Ĺ�̨�Ϲ���һ������(paizi)��
LONG );
       set("exits", ([
		"east" : __DIR__"caroad_w1",
	]));
	set("item_desc", ([
		"paizi" : "����������бб��д�������֣�\n\n"
			"		       ������\n\n",
	]));
	set("objects", ([
		__DIR__"npc/chenlaotou" : 1,
		__DIR__"npc/youren" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

