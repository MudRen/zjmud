//Room: huarui1.c

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
	([ //sizeof() == 3
		"south" : __DIR__"minju1",
		"west"  : __DIR__"yongtai-nankou",
		"east"  : __DIR__"huarui2",
		"north" : __DIR__"majiu",
	]));

	set("outdoors", "changan");
	setup();
}
