//Room: huanggong.c

inherit ROOM;

void create ()
{
	set ("short", "�ʹ����");
	set ("long", @LONG
�ʹ��������ȫ�����ģ�����������ƫ�����һ��Լ��ʮ�ɳ���
�ȵ������������߷ɳ�������������������������Ϊ����
LONG);
	set("exits", ([
		"south"   : __DIR__"bridge2",
		"north"   : __DIR__"bridge1",
		"east"   : __DIR__"fudian1",
		"west"   : __DIR__"fudian2",
	]));
	set("objects", ([
		__DIR__"npc/shiwei" : 4,
	]));

	setup();
}
