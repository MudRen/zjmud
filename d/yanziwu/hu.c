#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long",@LONG
����һ��֧���ڶ��С�ӣ����涼����Ҷ�����˽�������Ҷ�봬��
�����ɳɳ����������һƬ�ž���������磬���ŵ����Ļ��㣬�㲻��
����:  "��������һ���ӣ�Ҳ���ۣ�"
LONG );
	set("outdoors", "yanziwu");
	setup();
}
