//      zoulang3.c ����
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
������ѩɽ���ڵ����ȡ������е��İ����컨������
һЩ��֪��ȷ�к���ĵ�̣�ǽ�������Ǻ�ͨ�׵ķ𾭹�
�±ڻ��ˡ����ϵ��ż���󺣵�������
LONG );
	set("exits", ([
		"north"    : __DIR__"neidian",
		"eastdown" : __DIR__"zoulang1",
		"westdown" : __DIR__"zoulang2",
	]));
	setup();
}

