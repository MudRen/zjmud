//Room: piandian.c

inherit ROOM;

void create ()
{
  set ("short", "ƫ��");
  set ("long", @LONG
ƫ����������������̨���������ΰ����Ű������ķ����������
Ҳ�ǲ��ϣ���������һЩ���š�������������һ��Ҳ����������������
���ݵ���ɮ��������ɮ��ɫͨ�죬��������黨�����ֺ�ָ���죻��
����ɮȴ��ɫ���̣����������黨�����ֺ�ָ���졣��ɮ��ʽһģһ
����ȴƫ�������෴�����ߵ���ͨ����۱��
LONG);

	set("exits", ([
		"east"    : __DIR__"baodian",
	]));

	set("objects", ([
		__DIR__"npc/jingxuan" : 1,
		__DIR__"npc/jingming" : 1,
	]));

	setup();
}