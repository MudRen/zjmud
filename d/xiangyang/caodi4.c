// Room: /d/xiangyang/caodi4.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
	set("short", "�ݵ�");
	set("long", @LONG
������������Ĳݵء��ɹű���������������İ���ȫ��
���ˣ����Ｘʮ�ﶼû�����̡�
LONG );
	set("outdoors", "xiangyang");

	set("exits", ([
		"west"  : __DIR__"southgate2",
		"east"  : __DIR__"huapu",
	]));

/* 2002��3�£��̹���ļҽ�����ϣ�����ؼ�ȥ�ֻ��ˡ� --Pound
	set("objects", ([
		CLASS_D("hu") + "/cheng" : 1,
	]));
*/
	setup();
}

