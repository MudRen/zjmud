// senlin1.c

inherit ROOM;

#include <ansi.h>

void create()
{
	set("short", "��ľ԰");
	set("long", @LONG
������÷ׯ�İ�ľ԰����һ�ߵ���������ߵ���һ�������޾�
��Сɭ��һ��������������������������������кܶ�в�������
�ֵ�������ľ���Ա�����һ������(pai zi)��
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
	    "south" : __DIR__"keting",
	    "north" : __DIR__"neiyuan",
	    "east" : __DIR__"senlin2",
	    "west" : __DIR__"neitang",
	]));
	set("item_desc", ([ /* sizeof() == 1 */
	    "huang song" : "һ��ߴ�Ļ��ɣ���ס��������ߡ�\n",
	    "pai zi" : "��ľʥ�֣�����Ī�룬ֻ��ֱ�У�������\n",
	]));
	set("outdoors", "meizhuang");
	setup();
}

