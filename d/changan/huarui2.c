//Room: huarui2.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ�������һ��������Ĵ����Ҳ�ǳ����ǵľ�������һ��
��ʯ���̳ɵĽַ����ϱ߿ɼ�һЩ���סլ��������һ��С��ݣ���ͷ
�д�������Ʈ��������ζ����Զ�������Ҽһ������׵����������д�
���˼�ե���͵Ĵ���ζ��
LONG);
	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"minju2",
		"north" : __DIR__"mianguan",
		"west" : __DIR__"huarui1",
		"east" : __DIR__"huarui3",
	]));

	set("outdoors", "changan");
	setup();
}
