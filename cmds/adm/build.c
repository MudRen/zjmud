// build.c
// created by doing

#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	if (! SECURITY_D->valid_grant(me, "(admin)"))
	{
		write("��û��Ȩ�ޱ���" + LOCAL_MUD_NAME() + "�İ汾��\n");
		return 1;
	}

	if (! arg)
		return notify_fail("ָ���ʽ: build <·����> | version | new | cancel\n");

	if (arg == "version")
		return VERSION_D->generate_version();

	if (arg == "cancel")
		return VERSION_D->build_cancel();

	if (arg == "new")
		return VERSION_D->build_new();

	if (arg[0] != '/')
		return notify_fail("���������һ��������·�����ſ��ԡ�\n");

	return VERSION_D->build_path(arg);
}

int help (object me)
{
	write(@HELP
ָ���ʽ: build <·����> | version | cancel | new

�����������ڷ�����MUDLIB�汾�����������·�������͸��µ�ǰ��
����ĳһ��·��������·�����ķ�ʽ�����������ǰ汾Ŀ¼�µ��ļ���

build version ���ɵ�ǰMUDLIB�����·����汾��
build cancel  ��ֹ��ǰ���ɰ汾�Ĳ������ָ���ǰ�İ汾��Ϣ��
build /       ǿ�д��¸��ǰ汾Ŀ¼�µ������ļ���
build new     �����µİ汾�š�

ע�⣬build cancel��һ���ƻ����������ԵĲ�������Ϊ���������
�����ָܻ�Ӧ�ñ����ǵİ汾����ʹ����build cancel�Ժ󣬽���
����build / �������������а汾��

build new �������build <·����>ʹ�õģ����ֱ������һЩ·��
�Ժ��б�Ҫ����һ���µİ汾�ţ��ѱ�����վ���Զ����¡�

HELP );
	return 1;
}
