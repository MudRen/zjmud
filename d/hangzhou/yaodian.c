// yaodian.c
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "��������");
	set("long", @LONG
����һ������������ҩ�ã���ǽ����һ����ҩ�񡣼��������æ
���������µش�С������ץҩ��ҩ��ǰ����һ�����ӣ�����һλ����
����Ϊ�˰�������������ҽ�����ࡣ
    ��̨�Ϸ��߹�һ��������.
LONG);
	set("exits", ([
	    "west"      : __DIR__"road14",
	]));
	set("no_fight","1");
	set("no_beg","1");
	set("objects", ([
	    __DIR__"npc/huqingyu" : 1,
	]));
	set("item_desc", ([
	    "�����ӡ�" : "������۸���ҩƷ��\n"
	]));

	set("no_clean_up", 0);
	setup();
}