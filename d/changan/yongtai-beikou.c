//Room: yongtai-beikou.c

inherit ROOM;

void create ()
{
	set ("short", "��̩����");
	set ("long", @LONG
����ֵ�����ͷ��һ�����ɶ�ߵ����֮�ϣ���������յ����ĵ�
����ÿ��ĺɫ���٣�����ƻ�ͨ����������һ���鱦�У���������ɢ��
���˵���ⱦ�����ܶ฾��·�����ﶼ����Ҫ������һ�ơ��Ϸ�ͨ����
̩�����
LONG);
	set("exits", 
	([ //sizeof() == 1
		"east" : __DIR__"qixiang1",
		"north" : __DIR__"zhubaohang",
		"south" : __DIR__"yongtai-dadao1"
	]));

	set("outdoors", "changan");  
	setup();
}
