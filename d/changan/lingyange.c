//Room: lingyange.c

inherit ROOM;

void create()
{
	set("short", "���̸�");
	set("long", @LONG
խխ���ţ�խխ��¥�ݣ��������ŵķ��䣬�������ܿ��Ӵ��ڿ�
��ȥ��������ɫ������ǰ��
LONG);
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"fengxu4",
	]));

	setup();
}
