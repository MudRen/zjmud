//Room: huarui5.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ�������һ��������Ĵ����Ҳ�ǳ����ǵľ�������һ��
��ʯ���̳ɵĽַ����ϱ߿ɼ�һЩ���סլ����ͷ�д�������Ʈ�����
����ζ����Զ�������Ҽһ������׵����������д��˼�ե���͵Ĵ���
ζ��·�������С���������ֳ�����ˣ�š�����
LONG);
	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"minju5",
		"west" : __DIR__"huarui4",
		"east" : __DIR__"huarui6",
		"north" : __DIR__"zahuopu",
	]));

	set("outdoors", "changan");
	setup();
}
