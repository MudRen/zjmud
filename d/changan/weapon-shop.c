//Room: weapon-shop.c

#include <ansi.h>

inherit ROOM;

void create ()
{
	set ("short", "������");
	set ("long", @LONG
�����Ǳ����ꡣ���ﵽ�����������������ۻ����ҡ��������ϰ���
���ֱ�����ʮ�˰�������Ӧ�о��У�������ȫ���������ϰ���Ľ������
�Ĵ��ˡ���ǽ�ϻ�д��һ��ʫ(poem)��
LONG);
	set("exits", 
	([ //sizeof() == 1
		"north" : __DIR__"qixiang6",
	]));
	set("item_desc", ([
		"poem": HIR @TEXT
	��ˮ���������䣬׳ʿһȥ��������
	ƴ����ƾ���߽�������Ψ�и����գ�
TEXT NOR
	]) );
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/murong-hao" : 1,
	]));

	set("no_clean_up", 0);
	setup();
}
