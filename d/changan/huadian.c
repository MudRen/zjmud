//Room: huadian.c

inherit ROOM;

void create ()
{
	set ("short", "����");
	set ("long", @LONG
��û���ţ�����Ѿ��ŵ�һ�����µĻ��㡣���и���������������
Ŀ�������������֡����Ͳ��ָߵ͹�����������������Ц����ӭ����
����е�С���Ӷ�ϲ�����������������ѡһЩ�������ʻ��͸����ϵ�
���
LONG);
	set("exits", 
	([ //sizeof() == 1
		"south" : __DIR__"huarui3",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/girl" : 1,
	]));

	setup();
}
