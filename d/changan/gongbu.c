//Room: gongbu.c

inherit ROOM;

void create ()
{
	set ("short", "����");
	set ("long", @LONG
�����������ϰ�����Ĺ����������е�������û����������������
��������ĸ��������Դ��������ӹ��γ��Ϻõ��òģ�Ȼ�������
����ת�˸��ء������Ĺ������澡�����µ��ܹ��ɽ���
LONG);
	set("exits",  ([ //sizeof() == 2
		"west"  : __DIR__"nanan-dadao",
		"north" : __DIR__"gongbu-tong",
		"south" : __DIR__"gongbu-shi",
	]));

	setup();
}
