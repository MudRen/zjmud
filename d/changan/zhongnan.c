// Room:/d/changan/zhongnan.c

inherit ROOM;

void create()
{
	set("short",  "����ɽ��");
	set("long",  @LONG
����ɽ�ֳ�̫��ɽ���೤���ǰ�ʮ������С������������
����֮˵���ݴ���������ɽ�н�����������ٵ���Խ����ɽ�ڣ���
��������ƣ�����ȴû��һ��·������ɽ���������������Ĵ����
����ǰ����ԭ��
LONG);
	set("exits",  ([  /*  sizeof()  ==  4  */
		"east"  :  __DIR__"road2",
		"west"  :  __DIR__"road3",
	]));
	set("outdoors", "changan");

	setup();
}
