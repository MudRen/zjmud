// liaotian.c

inherit ROOM;

int is_chat_room() { return 1; }

void create()
{
	set("short", "�͵�跿");
	set("long", @LONG
���������ݿ�ջ�Ĳ�¥������������µ������������죬��С��
�������ڶ�����м䣬æ����ͣ���Ա���һ��С�ţ�������һЩ����
�������������ķΡ�
LONG );
	set("no_fight", 1);
	set("no_sleep_room", 1);
	set("exits", ([
		"south" : __DIR__"kedian",
		"west"   : __DIR__"xiaohuayuan",
	]));
	set("objects", ([
	     __DIR__"npc/qi"     : 1,
	     "/adm/npc/bao"    : 1,
	]));

	setup();
}
