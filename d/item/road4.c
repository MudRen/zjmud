// road4.c С��

inherit ROOM;

void create()
{
	object ob;

	set("short", "С��");
	set("long", @LONG
����һ�����ѵ�С������������ͨ��ɽ�·���Ϲ⻬ƽʵ��������
�������������������Ѿ���ɽ���ˣ�ɽ������һЩ������������һЩ
é�ݡ�ֻ�ж��߲�Զ�ĵط���һ��Сש������Ͳ����ʱ��ʱð��һ�ɹɺ�
�̣������Ǵ���
LONG );

	set("exits", ([
		"southwest" : __DIR__"road3",
		"east"      : __DIR__"road5",
	]));

	set("objects", ([
		__DIR__"npc/zhang" : 1,
	]));

	set("outdoors", "suzhou");
	setup();
}

