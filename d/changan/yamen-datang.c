//Room: yamen-datang.c

inherit ROOM;

void create ()
{
	set ("short", "����������");
	set ("long", @LONG
����������֮����һ������֮�ƣ����������ľ�������ǰ��һ�ź�
ľ��������������֪�����ˡ�����һ�����ң�д��"��������"�ĸ��̽�
���֡�����վ����һλ��ʦү��
LONG);
	set("exits", 
	([ //sizeof() == 1
		"north" : __DIR__"yamen",
	]));
	set("objects", 
	([ //sizeof() == 2
		__DIR__"npc/zhifu" : 1,
		__DIR__"npc/shiye" : 1,
	]));

	setup();
}
