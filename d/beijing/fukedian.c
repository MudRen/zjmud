inherit ROOM;

void create()
{
	set("short", "������ջ");
	set("long", @LONG
���Ǿ��ǻ���·��ͷ�ڽֵ�һ�ҿ�ջ����ջ����ǰ������һ���ͻ���ɽ
�ľ޻������Ź��Ŷ�ԧ��������ϵ�ż���СС�Ļ�ͭ���塣΢���ӹ�������
��������ö��Ķ����������к�����������ջ����
LONG );
	set("no_fight", 1);
	set("valid_startroom", 1);
	set("objects", ([
		__DIR__"npc/xiaoer3" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"kediandayuan",
		"south" : __DIR__"fu_2",
	]));
	set("no_clean_up", 0);
	setup();
}

