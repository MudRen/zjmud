//Room: yamen.c

inherit ROOM;

void create ()
{
	set ("short", "���Ŵ���");
	set ("long", @LONG
���ǳ����ǵ����Ŵ��ţ�Ҳ�ǳ�������ߵ��������������︺���
�����Ĵ���С�顣������͵��������С�������ǷŻ�ɱ�˵�ǿ������
���������ܵ�Ӧ�еĴ�����ǽ������һ�Ÿ�ʾ(gaoshi)
LONG);
	set("item_desc", ([
		"gaoshi": ""
	]) );
	set("exits", 
	([ //sizeof() == 2
		"south" : __DIR__"yamen-datang",
		"north" : __DIR__"qinglong3",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/yayi" : 4,
	]));

	setup();
}
