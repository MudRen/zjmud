// tyroad1.c ʯ��
// by Marz 

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
����һ������ʵ��ʯ��·����ʱ���н���ͺ����˴��������߹���̧ͷ��
������ΰ��������������������֮�У�Ρ��׳�ۣ�����һ��ʯ��ͨ��ɽ�£���
Լ�ɼ�Զ���һ�ƬƬ��������Ŀ��
LONG );
	set("outdoors", "wudang");
	set("exits", ([
		"southwest" : __DIR__"guangchang",
		"east" : __DIR__"tyroad2",
	]));
	set("no_clean_up", 0);
	setup();
}
