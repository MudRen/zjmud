//Room: yaopu.c

#include <ansi.h>

inherit ROOM;

void create ()
{
	set ("short", "�ش���ҩ��");
	set ("long", @LONG
���ǳ�����һ�Ҹոտ��Ų��õ�ҩ�̣��ഫԭ�����ϰ��ǽ�������
���ص�ҽ���е���ҽ���ֶο�֪һ����ҩ���еİ���Ҳʮ�ֿ���������
���ڿ�Ļ�Ʋ��ĸɸɾ�����ǽ�Ϲ����˱���������л��(bian)��
LONG);
	set("item_desc", (["bian" : HIW" ���ֻش� \n"NOR"\n", ]));
	set("exits", 
	([ //sizeof() == 1
		"south" : __DIR__"qixiang6",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/doctor" : 1,
	]));

	set("no_clean_up", 0);
	setup();
}
