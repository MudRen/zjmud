// houting.c
inherit ROOM;
void create()
{
	set("short", "�����̺���");
	set("long", @LONG
���������̵����³���--Ǳ������������С��ǰ�������Ŵ����Σ�
���߰������С�ʣ�����������������ʹƽʱ������λ�á�
LONG );
	set("exits", ([
		"south" : __DIR__"dating",
	]));

	set("objects", ([
		CLASS_D("shenlong")+"/yin": 1,
	]));
	set("outdoors","shenlong");
	setup();
}

