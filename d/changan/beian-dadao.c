//Room: beian-dadao.c

inherit ROOM;

void create ()
{
	set ("short", "�������");
	set ("long", @LONG
�����ǵ����ֱ����������ֱ���������֣�����������ÿͺ���
�˶��������������������������򱱾��ǳ����ǵı����ţ�������
�ǹʻʹ��İ׻��֡�
LONG);
	set("exits", 
	([ //sizeof() == 2
		"north" : __DIR__"beian-daokou",
		"south" : __DIR__"baihu2",
	]));

	set("outdoors", "changan");
	setup();
}
