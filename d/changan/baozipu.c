//Room: baozipu.c

inherit ROOM;

void create ()
{
	set ("short", "������");
	set ("long", @LONG
������İ��貢���Ǻܽ������������˼���Բľ����������������
�ҵķ��˼��ѳ������ӡ�һ��С���û����ɵĿ��ڹ�̨�ߣ��������
����ֻ���������������˸��к�����������������Ⲣ����ô�á�
LONG);
	//set("item_desc", ([" *** " : " *** ", ]));
	set("exits", 
	([ //sizeof() == 1
		"north" : __DIR__"yongtai-nankou",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/huoji" : 1,
	]));

	set("no_clean_up", 0);
	setup();
}
