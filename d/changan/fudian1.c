//Room: fudian1.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
�������ϻʹ����Ϊ�ͣ���߳����������������ж࣬����һ��
ʮ�ɵĳ����ߵ����ӻʹ����������һ���������Գ�һ����ϵ����
����ɭ��
LONG);
	set("exits", 
	([ //sizeof() == 1
		"west" : __DIR__"huanggong",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/shiwei" : 2,
	]));
	
	setup();
}
