//Room: xiaojinghu.c

inherit ROOM;

void create ()
{
	set ("short", "С����");
	set ("long", @LONG
������ǳ����ǵ�С�����ˡ�С��������������Ǻܴ󣬵�̨ͤ¥
�󣬼�ɽ����ȴҲ���еġ����������ؼ򵥣������ݻ�����ˮ��������
���������˵ķ����������ƺ�����ʧ�ˡ�Ϧ������ʱ���е��������ǵ�
����ɢ��������С��
LONG);
	set("exits",([//sizeof() == 1
		"south" : __DIR__"huarui4",
	]));
	
	set("resource", ([ /* sizeof() == 1 */
		"water" : 1,
	]));
	
	set("outdoors", "changan");
	setup();
}
	