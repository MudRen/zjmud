//Room: mianguan.c

inherit ROOM;

void create ()
{
	set ("short", "���");
	set ("long", @LONG
��˵�����ʮ����ǰ���������ˣ����Ҳ��۹η����꣬���۹����
�ڣ�����ݴ�δ��Ϣ��һ�졣���Գ����ҹ���񶼷��ĵúܣ���Ϊ����
�ؼ����Ų����ţ����ٻ����������ŵ���������һ���������ڵ�ţ��
�档
LONG);
	//set("item_desc", ([" *** " : " *** ", ]));
	set("exits", 
	([ //sizeof() == 1
		"south" : __DIR__"huarui2",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/laozhang" : 1,
	]));

	set("no_clean_up", 0);
	setup();
}
