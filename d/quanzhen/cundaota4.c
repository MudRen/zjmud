// cundaota4.c �������
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", @LONG
�����Ǵ���������������ݵ�����͵��˾�ͷ��ǽ���Ͽ��ż�
������(window)������������������������ж���
LONG
	);
	set("exits", ([
		"southdown" : __DIR__"cundaota3",
	]));
	set("objects", ([
		__DIR__"npc/zhangjing" : 1,
	]));

	set("item_desc", ([
		"�����ڡ�": "�������Ʈ�����ƺ���һ���־Ϳ���ץסһƬ��\n",
	]) );

	set("count",1);
	setup();
}

