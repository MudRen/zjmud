//Room: /d/dali/hole.c
inherit ROOM;
void create()
{
	set("short","֥�ƶ�");
	set("long",@LONG
���Ż��۽��붴�ڣ��ػ����У����ã�����һ����Ȼ���ʣ�ʯ��
�飬ʯ��ʯ����������͸��������ʤ�����ձ�Ӱ�����´����ң�Ϫ
�ƽ�ˮ�������ֺ���ʯ��δ䣬���Ŀɰ���
LONG);
	set("outdoors", "dali");
	set("exits",([ /* sizeof() == 1 */
	    "out"      : __DIR__"changhu",
	]));
	set("no_clean_up", 0);
	setup();
}

